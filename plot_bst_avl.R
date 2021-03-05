library(ggplot2)
library(dplyr)

results_insert <- read.table("D:/UL/Algorithms and complexity/project2/project2/results_insert_proj2.txt", 
                    sep = "" , header = T, na.strings ="", stringsAsFactors= F)

dfbst_random <- data.frame(results_insert [,1], results_insert [,2])
dfbst_ordered <- data.frame(results_insert [,1], results_insert [,3])
dfbst_nearly_ordered <- data.frame(results_insert [,1], results_insert [,4])
dfavl_random <- data.frame(results_insert [,1], results_insert [,5])
dfavl_ordered<- data.frame(results_insert [,1], results_insert [,6])
dfavl_nearly_ordered  <- data.frame(results_insert [,1], results_insert [,7])

png("proj2_insert.jpeg", width = 840)

plot(dfbst_nearly_ordered[,1], dfbst_nearly_ordered[,2], "l", lty=3, col = "red", main = "Solid - random, dashed - ordered, dotted - nearly ordered.
Red - BST, blue - AVL", 
       xlab = "size", ylab = "time")
lines(dfbst_ordered[,1], dfbst_ordered[,2], "l", lty=2, col = "red")
lines(dfavl_ordered[,1], dfavl_ordered[,2], "l", lty=2,col = "blue")
lines(dfbst_random[,1], dfbst_random[,2], "l", col = "red")
lines(dfavl_random[,1], dfavl_random[,2], "l", lty=1, col = "blue")
lines(dfavl_nearly_ordered[,1], dfavl_nearly_ordered[,2], "l", lty=3,col = "blue")

dev.off()


results_search <- read.table("D:/UL/Algorithms and complexity/project2/project2/results_search_exists_proj2.txt", 
                             sep = "" , header = T, na.strings ="", stringsAsFactors= F)

dfbst_random <- data.frame(results_search [,1], results_search [,2])
dfbst_ordered <- data.frame(results_search [,1], results_search [,3])
dfbst_nearly_ordered <- data.frame(results_search [,1], results_search [,4])
dfavl_random <- data.frame(results_search [,1], results_search [,5])
dfavl_ordered<- data.frame(results_search [,1], results_search [,6])
dfavl_nearly_ordered  <- data.frame(results_search [,1], results_search [,7])

png("proj2_search.jpeg", width = 840)


plot(dfbst_nearly_ordered[,1], dfbst_nearly_ordered[,2], "l", lty=3, col = "red", main = "Solid - random, dashed - ordered, dotted - nearly ordered.
Red - BST, blue - AVL", 
     xlab = "size", ylab = "time")
lines(dfbst_ordered[,1], dfbst_ordered[,2], "l", lty=2, col = "red")
lines(dfavl_ordered[,1], dfavl_ordered[,2], "l", lty=2,col = "blue")
lines(dfbst_random[,1], dfbst_random[,2], "l", col = "red")
lines(dfavl_random[,1], dfavl_random[,2], "l", lty=1, col = "blue")
lines(dfavl_nearly_ordered[,1], dfavl_nearly_ordered[,2], "l", lty=3,col = "blue")

dev.off()

png("proj2_search_bst_avl.jpeg", width = 840, type = "windows")

plot(dfavl_random[,1], dfavl_random[,2], "l", lty=1, col = "blue", main = "Red - BST, blue - AVL", 
     xlab = "size", ylab = "time")
lines(dfbst_random[,1], dfbst_random[,2], "l", col = "red")

dev.off()


results_search_abs <- read.table("D:/UL/Algorithms and complexity/project2/project2/results_search_absent_proj2.txt", 
                             sep = "" , header = T, na.strings ="", stringsAsFactors= F)

dfbst_random <- data.frame(results_search_abs [,1], results_search_abs [,2])
dfbst_ordered <- data.frame(results_search_abs [,1], results_search_abs [,3])
dfbst_nearly_ordered <- data.frame(results_search_abs [,1], results_search_abs [,4])
dfavl_random <- data.frame(results_search_abs [,1], results_search_abs [,5])
dfavl_ordered<- data.frame(results_search_abs [,1], results_search_abs [,6])
dfavl_nearly_ordered  <- data.frame(results_search_abs [,1], results_search_abs [,7])

png("proj2_search_excluded.jpeg", width = 840)

plot(dfavl_random[,1], dfavl_random[,2], "l", lty=1, col = "blue", main = "Solid - random, dashed - ordered, dotted - nearly ordered.
Red - BST, blue - AVL", 
     xlab = "size", ylab = "time")
lines(dfbst_ordered[,1], dfbst_ordered[,2], "l", lty=2, col = "red")
lines(dfavl_ordered[,1], dfavl_ordered[,2], "l", lty=2,col = "blue")
lines(dfbst_random[,1], dfbst_random[,2], "l", col = "red")
lines(dfbst_nearly_ordered[,1], dfbst_nearly_ordered[,2], "l", lty=3, col = "red")
lines(dfavl_nearly_ordered[,1], dfavl_nearly_ordered[,2], "l", lty=3,col = "blue")

dev.off()

png("proj2_search_bst_avl_excluded.jpeg", width = 840, type = "windows")

plot(dfavl_random[,1], dfavl_random[,2], "l", lty=1, col = "blue", main = "Red - BST, blue - AVL", 
     xlab = "size", ylab = "time")
lines(dfbst_random[,1], dfbst_random[,2], "l", col = "red")

dev.off()
