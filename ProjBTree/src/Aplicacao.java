public class Aplicacao {
    public static void main(String[] args) {
        BTree b = new BTree();

        for(int i=1; i<10000; i++)
            b.inserir(i,0);

        for(int i=1; i<10000; i++)
            b.exclusao(i);

        b.in_ordem();
    }
}
