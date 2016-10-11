pq = read.table(file.choose())
plot(pq$V1,pq$V2, type="l", col="blue", ylab="Comparações", xlab="Tamanho")
legend('topleft',c("PQ"),lty=1,col=c('red'), bty=2)