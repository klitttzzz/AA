set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'grafica2_tiempo_Lin_vs_Bin.png'

set title "Comparación Tiempo Real: Búsqueda Lineal vs Binaria"
set xlabel "Tamaño del Diccionario (N)"
set ylabel "Tiempo (segundos)"
set grid
set key left top box
# Formato científico para el eje Y porque los tiempos son muy pequeños
set format y "%.1e"

# --- DEFINICIÓN MANUAL DE LA CURVA (Evita error Singular Matrix) ---
# Pendiente calculada de tus datos: 0.000007 / 10000 = 7e-10
f_lineal_manual(x) = 7.0e-10 * x

title_lin = "Ajuste Lineal (y = 7.0e-10 * x)"

# --- GRAFICAR ---
plot "lineal_uniforme.dat" using 1:2 with points pt 7 ps 0.8 lc rgb "red" title "Datos Lineal", \
     f_lineal_manual(x) with lines lw 2 lc rgb "red" title title_lin, \
     "binaria_uniforme.dat" using 1:2 with linespoints pt 5 ps 0.8 lc rgb "blue" title "Datos Binaria (Tiempo ~ 0s)"