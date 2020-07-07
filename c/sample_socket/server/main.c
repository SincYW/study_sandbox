#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 参考サイト
// https://linuxjm.osdn.jp/html/LDP_man-pages/man2/socket.2.html


#define MAXPENDING 5 // 同時にキューイング可能な接続数
#define RECV_BUFF_SIZE 32 // 受信バッファサイズ
#define PORT 8000

void exitProgramWithError(const char* msg) {
  perror(msg);
  exit(1);
}

//
// クライアントからデータを受信する
// in: acceptで受け付けた、クライアント用のソケットファイルディスクリプタ
// return: なし
//
void recvClientData(int clientSockFd) {

  char buffer[RECV_BUFF_SIZE] = {0}; // サイズは適当
  int recvSize = 0; // 受信サイズ

  // 最後の０は、ソケットの動作をデフォルトから変えるかというフラグ
  // 今回はデフォルトで良いので、０を渡す
  if( ( recvSize = recv(clientSockFd, buffer, RECV_BUFF_SIZE, 0) ) < 0 ) {
    close(clientSockFd);
    exitProgramWithError("recv error.\n");
  }

  // メッセージを受信し続ける
  while( 0 < recvSize ) { // 受信サイズが０になった時点でデータの受取は終了

    // 念のために初期化
    memset(buffer, 0x00, RECV_BUFF_SIZE);

    // もらったデータを、熨斗をつけて返す
    if ( send(clientSockFd, buffer, recvSize, 0) != recvSize ) {
      close(clientSockFd);
      exitProgramWithError("send error.\n");
    }

    // まだデータが残っていないか確認のために、受信を行う
    // 受信を行った時点で、バッファはお掃除されている
    if( ( recvSize = recv(clientSockFd, buffer, RECV_BUFF_SIZE, 0) ) < 0) {
      close(clientSockFd);
      exitProgramWithError("recv error.\n");
    }
  }

  close(clientSockFd);

}

//
// Main
//
int main(int argc, char** argv) {

  // ソケットファイルディスクリプタ
  // ソケットの実態は番号というだけです。
  // その番号と、OS内部で作ったソケットを結びつけてるだけです。
  // で、通信できていないソケットは−１になるので、初期化値は-1が良いかな。
  int sockfd = -1;
  int clientSockfd = -1;

  // クライアント側の構造体の長さ
  int writer_len = 0;

  // ソケットの情報を入れるための構造体を宣言
  struct sockaddr_in reader_addr;
  struct sockaddr_in writer_addr;

  // ソケットを作る
  // PF_INET: ソケットを作る際に、インターネット用のプロトコルを使用する
  // SOCK_STREAM: ソケットの種類。信頼性の高い双方向通信用のソケットを使用する
  // IPPROTO_TCP: PF_INETかつ、SOCK_STREAM指定なのでTCP/IPを使用する
  if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    exitProgramWithError("socket error\n");
  }

  // ソケット用の構造体を初期化
  memset(&reader_addr, 0x00, sizeof(reader_addr));

  // AF_INET: インターネット用のアドレス形式
  reader_addr.sin_family = AF_INET;
  // データの受信を受け付ける相手を指定。
  // 0.0.0.0を指定しているので、誰でもウェルカム
  // htonl()は、今は気にしなくて良い。おまじない。気になる場合は、ネットワークバイトオーダーで検索。
  reader_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  // サーバ側が待ち受けるポートの指定。htons()は、htonl()のお友達。
  reader_addr.sin_port = htons(PORT);

  // ソケットと、自分の情報を合体
  if (bind(sockfd, (struct sockaddr *)&reader_addr, sizeof(reader_addr)) < 0) {
    exitProgramWithError("bind error.\n");
  }

  // --------------------------------------------------------------------------------------------------
  // ここ以降、処理で失敗したら必ずソケット変数はclose()します。
  // 一度作ってbindまでしまったソケットなので、放置するとOS内部にどんどんソケットが作られちゃいます
  // --------------------------------------------------------------------------------------------------

  // しっ。静かに。今クライアントからの接続要求を待ってる。
  // ソケットに、listen中のマークをつけてるイメージ。これがないと、クライアントからのconnectは全て拒否する
  if (listen(sockfd, MAXPENDING) < 0) {
    close(sockfd); // とじろおおお！
    exitProgramWithError("listen error.\n");
  }

  // 身体測定
  writer_len = sizeof(writer_addr);

  // ソケット用の構造体を初期化
  memset(&writer_addr, 0x00, sizeof(writer_addr));

  // クライアントから、握手しにくるのをひたすら待つ
  if ((clientSockfd = accept(sockfd,(struct sockaddr *)&writer_addr, &writer_len)) < 0) {
    close(sockfd);
    exitProgramWithError("accept error.\n");
  }

  // 受け付けた情報を全部お見せします！
  printf("Client Information: %s\n", inet_ntoa(writer_addr.sin_addr));

  // クライアントからデータを受信する自作関数を使う
  recvClientData(clientSockfd);

  // クライアントが閉じたので、こっちもソケットを閉鎖
  close(sockfd);
}



