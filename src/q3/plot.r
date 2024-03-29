library(ggplot2)

data <- read.csv(file = "./results/result.csv")
p <- ggplot(data, aes(x=sample, y=time, color=structure)) + geom_point()
ggsave("results/result.png", plot=p)

data <- read.csv(file = "./results/result_men.csv")
p <- ggplot(data, aes(x=sample, y=usage, color=structure)) + geom_point()
ggsave("results/result_mem.png", plot=p)

