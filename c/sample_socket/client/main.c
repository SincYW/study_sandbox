#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 受信バッファサイズ
#define RECV_BUFFER_SIZE 32
#define PORT 8000

void exitProgramWithError(const char* msg) {
  perror(msg);
  exit(1);
}

int main() {
  int sock = -1;
  struct sockaddr_in serverAddr;
  size_t serverAddrSize = 0;
  char buffer[RECV_BUFFER_SIZE] = {0};
  int totalRecvSize = 0;
  int oneTimeRecvSize = 0;
  int echoLength = 0;

  // ソケットの生成
  if( (sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP) ) < 0 ) {
    exitProgramWithError("sock error.\n");
  }

  // 身体測定
  serverAddrSize = sizeof(serverAddr);

  // サーバ情報を入れる箱をお掃除
  memset(&serverAddr, 0x00, serverAddrSize);

  serverAddr.sin_family = AF_INET;
  // サンプルで同じPCから来るので、とりあえずループバックアドレス
  // IPアドレスを示す文字列を、2進数に変換して渡す
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  // サーバ側でも書きましたが、詳細はネットワークバイトオーダーで検索
  serverAddr.sin_port = htons(PORT);

  // サーバへ接続要求
  if( connect(sock, (struct sockaddr *)&serverAddr, serverAddrSize ) < 0) {
    exitProgramWithError("connect error.\n");
  }

  // 身体測定
  echoLength = strlen("Hello World!!!");

  // サーバへデータを投げる(サンプルなのでとりあえず固定)
  if( send(sock, "Hello World!!!", echoLength, 0) < 0 ) {
    close(sock);
    exitProgramWithError("send error.\n");
  }

  totalRecvSize = 0;

  // 投げた文字列分が全部帰ってくるまで残業
  while(totalRecvSize < echoLength) {

    // 念のために初期化
    memset(buffer, 0x00, RECV_BUFFER_SIZE);

    // recvしたらバッファの中身は綺麗になるはず
    if( ( oneTimeRecvSize = recv(sock, buffer, RECV_BUFFER_SIZE - 1, 0) ) <= 0 ) {
      close(sock);
      exitProgramWithError("recv error. failed or connection closed by the server\n");
    }

    // 受信サイズを加算
    totalRecvSize += oneTimeRecvSize;
    // 受け取ったバッファーの最後は必ず末尾文字を入れて区切る
    buffer[oneTimeRecvSize] = '\0';

    // もらったものは報告する
    printf("Recieved: %s\n", buffer);

  }

  // おしまい
  close(sock);

  return 0;
}
