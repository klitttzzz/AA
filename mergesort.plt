# --- CONFIGURACIÓN GENERAL ---
# El fichero de salida será una imagen PNG
set terminal png
# Título general
set key top left
set grid

# --- GRÁFICA 1: Operaciones Básicas (Min, Avg, Max) ---
# Nombre de la imagen de salida
set output 'mergesort_obs.png'
# Título de la gráfica 1
set title "MergeSort: Operaciones Básicas vs N"
set xlabel "Tamaño (N)"
set ylabel "Operaciones Básicas (OBs)"

plot 'mergesort.csv' using 1:3 with linespoints title "OBs Promedio", \
     'mergesort.csv' using 1:4 with linespoints title "OBs Máximas", \
     'mergesort.csv' using 1:5 with linespoints title "OBs Mínimas"


# --- GRÁFICA 2: Tiempo de Ejecución ---
# Nombre de la imagen de salida
set output 'mergesort_time.png'
# Título de la gráfica 2
set title "MergeSort: Tiempo de Ejecución vs N"
set xlabel "Tamaño (N)"
set ylabel "Tiempo (segundos)"

plot 'mergesort.csv' using 1:2 with linespoints title "Tiempo Promedio"


# --- GRÁFICA 3: Comparación Teórica (Normalización) ---
# Nombre de la imagen de salida
set output 'mergesort_norm.png'
# Título de la gráfica 3
set title "MergeSort: Normalización vs N (Prueba de O(n log n))"
set xlabel "Tamaño (N)"
set ylabel "OBs / (N * log2(N))"

# Fórmula corregida con log()
plot 'mergesort.csv' using 1:($3 / ($1 * (log($1)/log(2)))) with linespoints title "Constante c = OBs / (N*log2(N))"