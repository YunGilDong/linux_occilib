Linux Mysql & MariaDB Lib
===================================

### 의존성 라이브러리 설치  ###
https://www.oracle.com/database/technologies/instant-client/linux-x86-64-downloads.html
- SDK Package (RPM) 다운로드 및 설치

SDK 설치:

```bash
$ apt-get install alien
$ alien -i oracle-instantclient12.1-devel-12.1.0.2.0-1.x86_64.rpm
```

의존Lib 설치:
```bash
$ sudo apt-get install libaio1 libaio-dev
```

라이브러리 링크 생성:
```bash
# oracle client library path
# 경로는 버전별로 다르기 때문에 확인 후 이동.
$ cd /usr/lib/oracle/19.5/client64/lib/ 	
$ ln -s libclntsh.so.19.5 libclntsh.so
$ ln -s libocci.so.19.5 libocci.so

```

### 참고 ###
https://mikesmithers.wordpress.com/2011/04/03/oracle-instant-client-on-ubuntu-with-added-aliens/
