import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        Patriciatree patriciaTree = new Patriciatree();

        /*patriciaTree.inserir("carro");
        patriciaTree.inserir("carrr");
        patriciaTree.inserir("carr");
        patriciaTree.inserir("caro");*/

        patriciaTree.inserir("bull");
        patriciaTree.inserir("buy");
        patriciaTree.inserir("sell");
        patriciaTree.inserir("stock");
        patriciaTree.inserir("bear");
        patriciaTree.inserir("bid");
        patriciaTree.inserir("stop");
        patriciaTree.inserir("bell");

        /*patriciaTree.inserir("bacacceaaeececd");
        patriciaTree.inserir("cabaaeadbbeecdcceddd");
        patriciaTree.inserir("cb");
        patriciaTree.inserir("cbbbcdceaa");
        patriciaTree.inserir("ddacbebbeccdbe");
        patriciaTree.inserir("eceebaedbdd");*/


        //exbição baseado na leitura de todas palavras da lingua portuguesa de forma aleatória
        /*BufferedReader leitor = new BufferedReader(new FileReader("palavra.txt"));
        String linha;
        ArrayList<String> linhas = new ArrayList<>();
        while ((linha = leitor.readLine()) != null) {
            linhas.add(linha.toLowerCase());
        }
        leitor.close();
        Collections.shuffle(linhas); //embaralha
        for(String linhaEmbaralhada : linhas){
            patriciaTree.inserir(linhaEmbaralhada);
        }
        */


        patriciaTree.exibir();
        System.out.println("Tamanho: " + patriciaTree.getPalavras().size());
        //for(String l : patriciaTree.getPalavras()) System.out.println(l);

        patriciaTree.exibeLevel();
    }


}