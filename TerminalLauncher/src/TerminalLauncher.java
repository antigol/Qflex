import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Scanner;

class TerminalLauncher
{
    public static void main(String args[]) throws IOException, InterruptedException
    {
    	Scanner sc = new Scanner(System.in);
    	Runtime rt = Runtime.getRuntime();
        String repertoire = "/Users/quentintalon/Dropbox/cmsInfo/CMS_Workspace/Qflex/qflex.app/Contents/Resources/";
        String ancien = "/opt/local/lib/";
        String nouveau = "@executable_path/../Resources/";

  /*      String libencours[] = {"libbz2.1.0.dylib", "libcrypto.1.0.0.dylib","libcurl.4.dylib","libexpat.1.dylib","libfontconfig.1.dylib",
        		"libfreetype.6.dylib","libiconv.2.dylib","libidn.11.dylib","libintl.8.dylib","libjbig.2.dylib","liblcms.1.dylib","liblcms2.2.dylib",
        		"libpoppler.19.dylib","libssl.1.0.0.dylib"};*/
        ArrayList<String> fichiers = FilesFinder.findFiles(repertoire);
        ArrayList<String> linkalink = new ArrayList<String>();
        linkalink = FilesFinder.findFiles(repertoire);
        
        String message;
        int position = 0;
/*        for(String lib:fichiers)
        {
        	System.out.print(position+" : ");
        	System.out.println(lib);
        	position++;
        }position=0;
        System.out.println("Choix linkage de lib n¼... ˆ changer");
        numLib = sc.nextInt();
        System.out.println(fichiers.get(numLib));

        System.out.println("Liste ˆ rentrer sans .dylib pour "+fichiers.get(numLib));
        message = sc.next();
        
        while(!message.equals("stop"))
        {
        	linkalink.add(message);
        	message = sc.next();
        }*/
        while(position < linkalink.size()) //Affichage des entrŽes des lib
        {
        	System.out.println(linkalink.get(position));
        	position++;
        }position = 0;
        
        System.out.println("OK ?");
        message = sc.next();
        if(message.equals("ok"))
        {     
        for(int i=0; i<fichiers.size();i++)
        {
        	for(int j=0; j<linkalink.size();j++)
        	{
                String action = "install_name_tool -change "+ancien+linkalink.get(j)+" "+nouveau+linkalink.get(j)+
                		" "+repertoire+fichiers.get(i);
                rt.exec(action);
                System.out.println(action);
                Thread.sleep(100);
        	}
        	String actionId = "install_name_tool -id "+nouveau+fichiers.get(i)+" "+repertoire+fichiers.get(i);
            rt.exec(actionId);
            System.out.println(actionId);
            Thread.sleep(100);
        }
        
        }
/*        if(message.equals("ok"))
        {
        	while(position < linkalink.size())
        	{
        String action = "install_name_tool -change "+nouveau+linkalink.get(position)+" "+ancien+linkalink.get(position)+
        		" "+repertoire+fichiers.get(numLib);
        rt.exec(action);
        System.out.println(action);
        position++;
        Thread.sleep(100);
        	}
        
        }*/
        System.out.println("fini");

    }
}
