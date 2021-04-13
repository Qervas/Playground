import org.apache.log4j.Logger;

import java.io.File;
import java.io.IOException;

public class Main {
    private static final Logger log = Logger.getLogger(Main.class);

    public static void main(String[] args) throws IOException {
        long start = System.currentTimeMillis();//开始计时
        //工作目录
        String working_dir = "/home/franktudor/Downloads";
        //待排序文件
        String sort_file = "sort.txt";
        //排序结果
        String sort_result = "result.txt";
        log.info("开始外部排序");
        ExtSort extSort = new ExtSort(11000,5);
        //升序排列
        String result = extSort.extSort(working_dir, sort_file, ExtSort.SortMode.ASC);
        File resultFile = new File(working_dir,result);
        if(resultFile.renameTo(new File(working_dir,sort_result))){
            log.info("排序完成，排序结果文件为:" + sort_result);
            log.info("排序耗时:"+(System.currentTimeMillis()-start)/1000.0+"秒");
        }else{
            log.error("排序失败，最终结果文件重命名失败");
        }
        start = System.currentTimeMillis();
        log.info("开始检查排序算法正确性");
        if(extSort.check(working_dir,sort_file,sort_result,ExtSort.SortMode.ASC)){
            log.info("排序算法是正确的");
        }else{
            log.error("排序结果不正确！");
        }
        log.info("排序检查耗时:"+(System.currentTimeMillis()-start)/1000.0+"秒");
    }
}
