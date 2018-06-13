set terminal postscript eps solid font "Times-Roman,25"
set xlabel "String length [KB]" center font "Times-Roman,25"
set ylabel "Time [s]" font "Times-Roman,25"
set xrange [0:4100]
set xtics 500
set yrange [0:150]
set output "text_time.eps"
set key inside t l Left
plot   "text_time.dat" using 1:2 w lp pt 7 ps 2 lw 2 notitle 





