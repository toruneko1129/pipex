make
./pipex || echo $?
./pipex 1 2 3 outfile || echo $?
./pipex infile hoge fuga outfile || echo $?
./pipex infile "   " "" outfile || echo $?
./pipex infile "/hoge" "/fuga" outfile || echo $?
./pipex infile "hoge -e -e -e -e" "fuga fuga" outfile || echo $?
