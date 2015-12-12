NGXCFGFOLDER=$(pwd)
sudo nginx -c $(echo $NGXCFGFOLDER"/nginx.cfg")
sudo nginx -s reopen
gcc hello.cpp -lfcgi -o repzs
spawn-fcgi -p 8000 -n repzs
