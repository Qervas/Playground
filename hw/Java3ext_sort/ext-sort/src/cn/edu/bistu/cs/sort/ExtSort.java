package cn.edu.bistu.cs.sort;
import org.apache.log4j.Logger;
import java.io.*;
import java.util.*;
/**
 * Java外部排序程序
 */
public class ExtSort {
    public enum SortMode{ASC,DESC}
    private static final Logger log = Logger.getLogger(ExtSort.class);
    /**
     * 对原始待排序文件进行分割处理时，每批次数据的记录个数。
     */
    private int initial_batch_size;
    /**
     * 归并排序时的归并路数，即每一轮同时可以将几个文件进行归并
     */
    private int merge_degree;
    public ExtSort(int initial_batch_size, int merge_degree) {
        this.initial_batch_size = initial_batch_size;
        this.merge_degree = merge_degree;
    }
    /**
     *
     * @param working_dir 工作目录
     * @param sort_file 待排序的原始文件
     * @param mode 排序模式，为ASC表示为升序排序（ascending），DESC为false表示为降序排序
     * @return 返回初始分割文件列表
     * @throws IOException 文件不存在或读写异常
     */
    private List<String> initialSortAndSplit(String working_dir, String sort_file, SortMode mode) throws IOException {
    	    //TODO 补充完整
    		return null;
    }
    /**
     * @param working_dir 工作目录
     * @param sort_file 待排序的原始文件
     * @param mode 排序模式，为ASC表示为升序排序（ascending），DESC为false表示为降序排序
     * @return 排序完成后的结果文件名
     * @throws IOException 文件不存在或读写异常
     */
    public String extSort(String working_dir, String sort_file, SortMode mode) throws IOException {
        //将文件按照设定的批次数据大小进行初始切分并排序
        log.info("开始执行初始文件分割和排序");
        List<String> fileNames = initialSortAndSplit(working_dir, sort_file, mode);
        log.info("初始文件分割和排序执行完毕，共产生:"+fileNames.size()+"个分割文件");
        //执行归并排序
        int round = 1;
        do {
            log.info("第"+round+"轮归并排序开始，待归并文件剩余:"+fileNames.size());
            fileNames = mergeSort(working_dir, fileNames, mode);//将所有fileNames的文件进行合并
            round++;
        } while (fileNames.size() > 1);
        return fileNames.get(0);
    }
    /**
     * 归并排序中的一轮，归并路数由merge_degree决定
     * @param working_dir 工作目录
     * @param fileNames 待归并的文件列表
     * @param mode 排序模式，为ASC表示为升序排序（ascending），DESC为false表示为降序排序
     * @return 归并后的文件列表
     * @throws IOException 文件不存在或读写异常
     */
    private List<String> mergeSort(String working_dir, List<String> fileNames, SortMode mode) throws IOException {
    	    //TODO 补充完整
    		return null;
    }
    /**
     * 检查working_dir目录下的srcFile文件和sortedFile文件是否具有相同的整数集合，同时检查sortedFile文件是否是有序的。
     * @param working_dir 工作目录
     * @param srcFile 原始待排序文件
     * @param sortedFile 排序后的文件
     * @param mode 排序模式，为ASC表示为升序排序（ascending），DESC为false表示为降序排序
     * @return 若排序结果是正确的，返回true，否则返回false
     */
    public boolean check(String working_dir, String srcFile, String sortedFile, SortMode mode) throws IOException {
    		//TODO 补充完整，选做
    		return true;
    }
}