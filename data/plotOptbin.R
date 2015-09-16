
plotScore <- function (file, main, varMax = 1000) {
    data <- read.csv(paste(file,".csv",sep=""))
    pdf(paste(file,".pdf",sep=""), width=5, height=5)

    par(mar=c(4,4,3,4)+0.1)
    plot(data$VAR, data$BINS, type="l", xlab="Size of the training set (in number of trajectories)", ylab="Optimal number of bins", main = main, ylim = c(0,120), xlim=c(0,varMax))
    par(new=TRUE)
    plot(data$VAR, data$SCORE, type="l",col="blue", xaxt="n",yaxt="n",xlab="",ylab="",ylim=c(0,2), xlim=c(0,1000))
    axis(4, col="blue", col.ticks="blue", labels=FALSE)
    at = axTicks(4)
    mtext(side = 4, text = at, at = at, col = "blue", line = 1)
    mtext("Logarithmic score", side=4, line=3, col="blue")

    dev.off()
}


plotScore("optbin","Initial Setting", varMax=2000)
plotScore("optbin_low-delay","Lower horizon (tau = 5)")
plotScore("optbin_high-delay","Higher horizon (tau = 20)")
plotScore("optbin_big-system","Bigger system (N = 200)")
plotScore("optbin_small-system","Smaller system (N = 50)")
plotScore("optbin_big-test","Bigger test set (200 trajectories)")
plotScore("optbin_small-test","Smaller test set (50 trajectories)")



plotCuts <- function (file, main, varMax = 1000) {
    data <- read.csv(paste(file,".csv",sep=""))
    #pdf(paste(file,".pdf",sep=""), width=5, height=5)

    x <- c()
    y <- c()
    for (i in 1:nrow(data)) {
        cuts <- strsplit(as.character(data$CUTS)[i],split=c(","))[[1]]
        x <- append(x,rep(data$VAR[i],length(cuts)))
        y <- append(y,cuts)
    }
    plot(x,y)
}


plotCuts("optbin_small-test","Cuts")
