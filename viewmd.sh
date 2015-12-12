pandoc -s -f markdown -t man "$1" | groff -T utf8 -man | less
