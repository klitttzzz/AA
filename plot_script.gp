set terminal pngcairo enhanced font "Verdana,10" size 1200,600
set output 'histograma_10M_muestras.png'
set style fill solid 0.5 border -1
set boxwidth 0.8
set title "Histograma de 10 Millones de Muestras (101 Intervalos)"
set xlabel "Intervalo de Números (ej: 40000 = rango 40000-49999)"
set ylabel "Frecuencia (Nº de apariciones)"
set yrange [0:*]
unset key
plot 'histogram_data.txt' using 1:2 with boxes