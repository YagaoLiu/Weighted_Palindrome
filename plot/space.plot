set terminal postscript eps solid font "Times-Roman,25"
set xlabel "String Length [MB]" center font "Times-Roman,25"
set ylabel "Maximum memory usage [MB]" font "Times-Roman,25"
set xrange [0:33]
set xtics 4
set yrange [0:22400]
set output "space.eps"
set key inside t l Left
plot "space_rank.dat" using 1:2 w lp pt 7 ps 2 lw 2 lc 1 title "ST-PSA",\
"space_uf.dat" using 1:2 w lp pt 13 ps 2 lw 2 lc 3 title "UF-PSA",\
"space_tree.dat" using 1:2 w lp pt 5 ps 2 lw 2 lc 2 title "PST"




