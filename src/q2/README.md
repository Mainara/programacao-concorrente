### 1.  (dev) CountDownLatch é um sincronizador disponível na sdk Java ([https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/CountDownLatch.html](https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/CountDownLatch.html)). Faça uma nova implementação da mesma ideia usando somente variáveis condicionais (wait, notify  e notifyAll) e a construção synchronized. Se precisar usar alguma coleção, use uma LinkedList ou ArrayList. Só é necessário implementar a API abaixo:
-   **void await()**
-   **void countDown()**

O CountDownLatch é um sincronizador que permite que uma ou mais Threads esperem até que um conjunto de operações sendo executadas em outras Threads sejam concluídas. Ele possui um contador como atributo, que pode ser decrementado ao chamar o método *countDown()*, quando o contador for igual a zero, a Thread que estava aguardando pode executar.

Nessa atividade, implementamos duas classes: **CountDownLatchPC** (recebe o contador como parâmetro) e **Worker**. Na classe **CountDownLatchPC** existem os métodos:
-   *await()*: verifica se o contador é maior que zero, caso seja, o método *wait()* é chamado, ou seja, a Thread atual irá "dormir";
-  *countDown()*: decrementa o contador e verifica se o mesmo é menor ou igual a zero, caso seja, o método *notifyAll()* é chamado, ou seja, todas as Threads serão acordadas.

Os dois métodos possuem *synchronized* nas suas declarações com a finalidade de garantir exclusão mútua.

A classe **Worker** foi criada para auxiliar os testes que fizemos. Essa classe estende a classe **Thread** e recebe um inteiro (*delay*), um objeto do tipo **CountDownLatchPC** e uma string para indicar seu nome. O método *run()* foi sobrescrito e possui o seguinte comportamento: chama o método *Thread.sleep(int delay)* (ou seja, coloca a Thread para dormir por determinado tempo), imprime (*nome_da_thread* finished) e chama o método *countDown()* da classe **CountDownLatchPC**.

Para testar, criamos um *main()* que possui a seguinte execução:
- cria uma instância da classe **CountDownLatchPC** passando 4 como parâmetro, ou seja, o contador é igual a 4;
-  cria 4 Threads do tipo **Worker** passando a instância de **CountDownLatchPC** para cada uma delas;
- inicializa as Threads;
- chama o método *await()* da classe **CountDownLatchPC**, ou seja, a Thread atual irá esperar a execução das outras 4 Threads;
- Imprime (*nome_thread_atual* has finished) ao terminar a execução de todas as Threads.
