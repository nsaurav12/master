import static org.junit.Assert.assertEquals;

import org.junit.Test;
import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Random;
import java.lang.Exception;

public class TestMessage2 {

	@Test
	public void test_welcome_message_2() throws Exception {
		String target_file = null;
		String tmp_target_file = null;
		
		webManager web =new webManager();
		FileManager fil = new FileManager();
		Random randomGenerator = new Random();
		
		String templatePath=".//test//xml_template";
		String [] listFiles = fil.listFiles(templatePath);
		fil.copyFile(templatePath, ".//test//request", listFiles);
		target_file =".//test//request//customer_create.xml";
		tmp_target_file =".//test//request//tmp_customer_create.xml";
		
		fil.replace(target_file,  tmp_target_file,"SW_CUST_AUTO_XXXX", "Test"+randomGenerator.nextInt(100000000));
		fil.replace(target_file,  tmp_target_file,"SW_PVT_XXX", (new SimpleDateFormat("MM/dd/yyyy HH:mm:ss"))
						.format(new Date()));

		web.callWebservice("http://172.16.191.247:7101/PortalAdapterWS/ACSOracleCBRMDef",".//test//request//customer_create.xml",".//test//response//customer_create.xml");
		File response_file = new File(".//test//response//customer_create.xml");
		assertEquals(fil.find(response_file, "<java:StatusDescription>OK</java:StatusDescription>") ,true);
		assertEquals("welcome", "welcome");

	}
 
}