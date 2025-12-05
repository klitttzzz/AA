set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'grafica1_promedio_OBs.png'

set title "Ajuste de Curvas OBs: Lineal vs Binaria"
set xlabel "Tamaño del Diccionario (N)"
set ylabel "Promedio de Operaciones Básicas (OB)"
set grid
set key left top box

# --- 1. DEFINICIÓN DE LA LINEAL (Teórica, ya que tus datos son perfectos) ---
# Tus datos son exactamente N/2, así que definimos la recta directamente
# para evitar el error "Singular Matrix" por varianza cero.
f_lineal_teorica(x) = 0.5 * x

# --- 2. AJUSTE DE LA BINARIA (Logarítmica) ---
# Aquí sí hacemos fit porque los datos tienen pequeños escalones
f_binaria_fit(x) = a * log(x) + b
a = 1.44; b = -1.0; # Valores iniciales seguros
fit f_binaria_fit(x) "binaria_uniforme.dat" using 1:3 via a, b

# Títulos para la leyenda
title_lin = "Ajuste Lineal (y = 0.5 * x)"
title_bin = sprintf("Ajuste Log (a=%.4f)", a)

# --- 3. GRAFICAR ---
plot "lineal_uniforme.dat" using 1:3 with points pt 7 ps 0.8 lc rgb "purple" title "Datos Lineal", \
     f_lineal_teorica(x) with lines lw 2 lc rgb "purple" title title_lin, \
     "binaria_uniforme.dat" using 1:3 with points pt 5 ps 0.8 lc rgb "green" title "Datos Binaria", \
     f_binaria_fit(x) with lines lw 2 lc rgb "green" title title_bin