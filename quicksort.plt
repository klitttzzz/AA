# --- CONFIGURACIÓN GENERAL ---
set terminal png
set key top left
set grid

# --- GRÁFICA 1: Operaciones Básicas (Min, Avg, Max) ---
set output 'quicksort_obs.png'
set title "QuickSort (Pivote 'median'): Operaciones Básicas vs N"
set xlabel "Tamaño (N)"
set ylabel "Operaciones Básicas (OBs)"

# Lee de 'quicksort_median.csv'
plot 'quicksort_median.csv' using 1:3 with linespoints title "OBs Promedio", \
     'quicksort_median.csv' using 1:4 with linespoints title "OBs Máximas", \
     'quicksort_median.csv' using 1:5 with linespoints title "OBs Mínimas"


# --- GRÁFICA 2: Tiempo de Ejecución ---
set output 'quicksort_time.png'
set title "QuickSort (Pivote 'median'): Tiempo de Ejecución vs N"
set xlabel "Tamaño (N)"
set ylabel "Tiempo (segundos)"

# Lee de 'quicksort_median.csv'
plot 'quicksort_median.csv' using 1:2 with linespoints title "Tiempo Promedio"


# --- GRÁFICA 3: Comparación Teórica (Normalización) ---
set output 'quicksort_norm.png'
set title "QuickSort (Pivote 'median'): Normalización vs N (Prueba de O(n log n))"
set xlabel "Tamaño (N)"
set ylabel "OBs / (N * log2(N))"

# Fórmula corregida con log() y lee de 'quicksort_median.csv'
plot 'quicksort_median.csv' using 1:($3 / ($1 * (log($1)/log(2)))) with linespoints title "Constante c = OBs / (N*log2(N))"