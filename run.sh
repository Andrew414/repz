./kill.sh
rm srepz
NGXCFGFOLDER=$(pwd)
sudo nginx -c $(echo $NGXCFGFOLDER"/nginx.cfg")
sudo nginx -s reopen
gcc $(ls *.c) $(pkg-config --cflags --libs libmongoc-1.0) -lfcgi -o srepz
LD_LIBRARY_PATH=/usr/local/lib spawn-fcgi -p 8000 -n srepz
