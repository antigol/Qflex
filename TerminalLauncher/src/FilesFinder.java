import java.io.File;
import java.util.ArrayList;

public class FilesFinder {

	public FilesFinder() {
		super();
	}
	
	public static ArrayList<String> findFiles(String directoryPath)
	{
		String monGrosString = "";
		ArrayList<String> fichiers = new ArrayList<String>();
		File directory = new File(directoryPath);
		if(!directory.exists()){
			System.out.println("Le fichier/rŽpertoire '"+directoryPath+"' n'existe pas");
		}else if(!directory.isDirectory()){
			System.out.println("Le chemin '"+directoryPath+"' correspond ˆ un fichier et non ˆ un rŽpertoire");
		}else{
			File[] subfiles = directory.listFiles();
			String message = "Le rŽpertoire '"+directoryPath+"' contient "+ subfiles.length+" fichier"+(subfiles.length>1?"s":"");
			System.out.println(message);
			for(int i=0 ; i<subfiles.length; i++){
			//	System.out.println(subfiles[i].getName());
				monGrosString = monGrosString +"\n" +subfiles[i].getName();
				fichiers.add(subfiles[i].getName());
			}
		}
		
		

		return fichiers;
	}

	public static void main(String[] args) {
	/*	FilesFinder finder = new FilesFinder();
		finder.findFiles("C:/temp");
		finder.findFiles("C:/toto");*/
	}
}
