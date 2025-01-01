set term x11 window "0x600007"

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb"#ffffff" behind
set key font ",6"
set tics font ", 6"
set sample 500
set bmargin 0
set lmargin 0
set rmargin 0
set tmargin 0
set term x11 size 288,143
unset mouse
set style line 1 lt 1 lw 2 pt 3 linecolor rgb "green"
set style line 2 lt 1 lw 2 pt 3 linecolor rgb "orange"
set style line 3 lt 1 lw 2 pt 3 linecolor rgb "red"
set style line 4 lt 1 lw 2 pt 3 linecolor rgb "black"
plot "./resources/evolution.txt" using 1:2 title 'Healthy' with lines ls 1 , "./resources/evolution.txt" using 1:3 title 'Sick' with lines ls 2, "./resources/evolution.txt" using 1:4 title 'Dead' with lines ls 3, "./resources/evolution.txt" using 1:5 title 'Burnt bodies' with lines ls 4
pause(1)
reread
