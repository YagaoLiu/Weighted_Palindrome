set terminal postscript eps solid font "Times-Roman,25"
set xlabel "Cumulative weight threshold z" center font "Times-Roman,25"
set ylabel "Maximal memory usage [MB]" font "Times-Roman,25"
set xrange [0:65]
set xtics 4 ("4" 4, "8" 8, "16" 16, "32" 32, "64" 64)
set yrange [0:3000]
set output "z_space.eps"
set key inside t l Left
plot   "z_space.dat" using 1:2 w lp pt 7 ps 2 lw 2 notitle 





