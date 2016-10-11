heap = read.table(file.choose())
plot(heap$V1,heap$V2, type="l", col="red", ylab="Comparações", xlab="Tamanho")
legend('topleft',c("HEAP"),lty=1,col=c('red'), bty=2)