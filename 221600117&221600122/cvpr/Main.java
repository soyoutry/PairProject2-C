import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;

public class  Spiter {
	// TODO Auto-generated method stub
	public static void main(String[] args) throws IOException {
		Document doc=Jsoup.connect("http://openaccess.thecvf.com/CVPR2018.py").maxBodySize(3000000).get();
		Elements listClass = doc.getElementsByAttributeValue("class", "ptitle");
		Document paper;
		int num=0;
		File file=new File("D:\\spider.txt");
		Writer out=new FileWriter(file);
			try {			
				System.out.print("爬取开始\n");
				for(Element element:listClass) {
					
					String link = element.getElementsByTag("a").attr("href");
					link="http://openaccess.thecvf.com/"+link;
					paper=Jsoup.connect(link).get();
					
					Element Etitle=paper.getElementById("papertitle");					
					Element Eabstr=paper.getElementById("abstract");
					String abstr=Eabstr.text();
					String title=Etitle.text();
					out.write(num+"\r\n");
					out.write("Title: "+title+"\r\n");
					out.write("Abstract: "+abstr+"\r\n"); 
					out.write("\r\n");
					out.write("\r\n");
					num++;
					out.flush();
				}
				System.out.print("爬取结束");
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			out.close();
			
		}
	
	
}