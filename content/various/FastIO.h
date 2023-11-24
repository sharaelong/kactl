/**
 * Author:
 * Description:
 */
#pragma once

namespace fio {
  const int BSIZE = 1<<18;
  char buffer[BSIZE];
  char wbuffer[BSIZE];
  char ss[30];
  int pos = BSIZE;
  int wpos = 0;
  int cnt = 0;

  inline char readChar() {
    if (pos == BSIZE) {
      fread(buffer, 1, BSIZE, stdin);
      pos = 0;
    }
    return buffer[pos++];
  }
    
  inline int readInt() {
    char c = readChar();
    while ((c < '0' || c > '9') && (c ^ '-')) c = readChar();
        
    int res = 0;
    bool neg = (c == '-');
    if (neg) c = readChar();
    while (c > 47 && c < 58) {
      res = res * 10 + c - '0';
      c = readChar();
    }

    if (neg) return -res;
    else return res;
  }
    
  inline void writeChar(char x){
    if (wpos == BSIZE) {
      fwrite(wbuffer, 1, BSIZE, stdout);
      wpos = 0;
    }
    wbuffer[wpos++] = x;
  }
    
  inline void writeInt(int x){
    if (x < 0) {
      writeChar('-');
      x = -x;
    }
    if (!x) {
      writeChar('0');
    } else {
      cnt = 0;
      while (x) {
        ss[cnt] = (x % 10) + '0';
        cnt++;
        x /= 10;
      }
      for (int j=cnt-1; j>=0; --j) writeChar(ss[j]);
    }
  }
    
  inline void my_flush() {
    if (wpos) {
      fwrite(wbuffer, 1, wpos, stdout);
      wpos = 0;
    }
  }
}
