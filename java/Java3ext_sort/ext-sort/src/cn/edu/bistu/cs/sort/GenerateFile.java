package cn.edu.bistu.cs.sort;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

/**
 * 生成一个包含大量整数的文件
 */
public class GenerateFile {
    public static void main(String[] args) throws IOException {
        File file = new File("/home/franktudor/Downloads/sort.txt");
        int numCount = 10000000;
        Random r = new Random();
        if (file.exists())
            file.delete();
        FileWriter fw = new FileWriter(file);
        for (int i = 0; i < numCount; i++) {
            fw.write(r.nextInt() + "\n");
        }
        fw.close();
    }
}
