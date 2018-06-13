set terminal postscript eps solid font "Times-Roman,25"
set xlabel "String Length [MB]" center font "Times-Roman,25"
set ylabel "Time [ms]" font "Times-Roman,25"
set xrange [0:12]
set xtics 4
set yrange [0:110000]
set output "time.eps"
set key inside t l Left
f(x) = a*x + b
g(x) = c*x*log(x) + d
h(x) = e*x*x + f*x + g
fit f(x) "time_rmq.dat" using 1:2 via a,b
fit g(x) "time_rmq.dat" using 1:2 via c,d
fit h(x) "time_rmq.dat" using 1:2 via e,f,g
plot "time_rmq.dat" using 1:2 w lp pt 13 ps 2 lw 2 lc 1 title "psa_rmq",\
	f(x) ls 7 lw 2 lc 3 title "linear fit curve",\
	h(x) ls 7 lw 2 lc 5 title "n^2 fit curve",\
	g(x) ls 7 lw 2 lc 4 title "nlogn fit curve"


