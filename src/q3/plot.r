library(ggplot2)

data <- read.csv(file = "./results/result.csv")
p <- ggplot(data, aes(x=sample, y=time, color=structure)) + geom_line()
ggsave("results/result.png", plot=p)

