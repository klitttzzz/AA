# --- Configuración General ---
# Define el tipo de terminal (fichero de imagen) y su tamaño
set terminal pngcairo size 1024,768 font 'Verdana,10'
# Activa la rejilla
set grid
# Pone la leyenda arriba a la izquierda
set key top left
# Etiqueta del eje X
set xlabel "Tamaño de la tabla (N)"


# --- Nombres de los Ficheros de Datos ---
# Asegúrate de que estos nombres coincidan con los ficheros que generes
# con el programa 'exercise5'

# Apartado 2: MergeSort
FILE_MERGESORT = "mergesort.log"

# Apartado 4: QuickSort (con pivote 'median')
FILE_QSORT_MEDIAN = "quicksort_median.log"

# Apartado 5: QuickSort (con los otros pivotes)
FILE_QSORT_AVG = "quicksort_avg.log"
FILE_QSORT_STAT = "quicksort_stat.log"


# [cite_start]--- Gráficas Apartado 5.2 (MergeSort) --- [cite: 7, 8]

# [cite_start]1. OBs (Medio, Peor, Mejor) para MergeSort [cite: 7]
set title "MergeSort: Operaciones Básicas (OBs)"
set ylabel "Número de OBs"
set output "mergesort_obs.png"
plot FILE_MERGESORT using 1:3 with linespoints title "OBs Promedio", \
     FILE_MERGESORT using 1:4 with linespoints title "OBs Máximo (Peor Caso)", \
     FILE_MERGESORT using 1:5 with linespoints title "OBs Mínimo (Mejor Caso)"

# [cite_start]2. Tiempo medio para MergeSort [cite: 8]
set title "MergeSort: Tiempo de Ejecución Promedio"
set ylabel "Tiempo (s)"
set output "mergesort_tiempo.png"
plot FILE_MERGESORT using 1:2 with linespoints title "Tiempo Promedio"


# [cite_start]--- Gráficas Apartado 5.4 (QuickSort - Pivote 'median') --- [cite: 9, 10, 11]

# [cite_start]3. OBs (Medio, Peor, Mejor) para QuickSort ('median') [cite: 9]
set title "QuickSort (Pivote 'median'): Operaciones Básicas (OBs)"
set ylabel "Número de OBs"
set output "quicksort_median_obs.png"
plot FILE_QSORT_MEDIAN using 1:3 with linespoints title "OBs Promedio", \
     FILE_QSORT_MEDIAN using 1:4 with linespoints title "OBs Máximo (Peor Caso)", \
     FILE_QSORT_MEDIAN using 1:5 with linespoints title "OBs Mínimo (Mejor Caso)"

# [cite_start]4. Tiempo medio para QuickSort ('median') [cite: 10]
set title "QuickSort (Pivote 'median'): Tiempo de Ejecución Promedio"
set ylabel "Tiempo (s)"
set output "quicksort_median_tiempo.png"
plot FILE_QSORT_MEDIAN using 1:2 with linespoints title "Tiempo Promedio"

# [cite_start]5. Comparativa Tiempo Medio (MergeSort vs QuickSort) [cite: 11]
set title "Comparativa: Tiempo de Ejecución Promedio"
set ylabel "Tiempo (s)"
set output "comparativa_tiempo.png"
plot FILE_MERGESORT using 1:2 with linespoints title "MergeSort", \
     FILE_QSORT_MEDIAN using 1:2 with linespoints title "QuickSort (median)"
     
# [cite_start]6. Comparativa OBs Medias (MergeSort vs QuickSort) [cite: 11]
set title "Comparativa: OBs Promedio"
set ylabel "Número de OBs"
set output "comparativa_obs_promedio.png"
plot FILE_MERGESORT using 1:3 with linespoints title "MergeSort", \
     FILE_QSORT_MEDIAN using 1:3 with linespoints title "QuickSort (median)"
     
# [cite_start]7. Comparativa OBs Máximas (MergeSort vs QuickSort) [cite: 11]
set title "Comparativa: OBs Máximo (Peor Caso)"
set ylabel "Número de OBs"
set output "comparativa_obs_max.png"
plot FILE_MERGESORT using 1:4 with linespoints title "MergeSort", \
     FILE_QSORT_MEDIAN using 1:4 with linespoints title "QuickSort (median)"


# [cite_start]--- Gráfica Apartado 5.5 (Comparativa Pivotes QuickSort) --- [cite: 11]

# [cite_start]8. Comparativa Tiempo Medio (Pivotes QuickSort) [cite: 11]
set title "QuickSort: Comparativa de Pivotes (Tiempo Promedio)"
set ylabel "Tiempo (s)"
set output "quicksort_pivotes_tiempo.png"
plot FILE_QSORT_MEDIAN using 1:2 with linespoints title "Pivote 'median' (primero)", \
     FILE_QSORT_AVG using 1:2 with linespoints title "Pivote 'median_avg' (medio)", \
     FILE_QSORT_STAT using 1:2 with linespoints title "Pivote 'median_stat' (estadístico)"

# --- Fin del script ---
print "¡Gráficas generadas!"