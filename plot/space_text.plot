set terminal postscript eps solid font "Times-Roman,25"
set xlabel "String length [KB]" center font "Times-Roman,25"
set ylabel "Maximal memory usage [MB]" font "Times-Roman,25"
set xrange [0:4100]
set xtics 500
set yrange [0:2000]
set ytics 200
set output "text_space.eps"
set key inside t l Left
plot   "text_space.dat" using 1:2 w lp pt 7 ps 2 lw 2 notitle 





