package fileTransfer;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileOutputStream;

import javax.imageio.ImageIO;

public class FileTransfer {
	
	public native byte[] fileTransfer(int w,int h,int[] im);
	
	static{
		System.loadLibrary("FileTransfer");
	}
		
	public static void main(String[] args){
		FileTransfer ft = new FileTransfer();
		File f = null;
		try{
			f = new File("D:\\img.jpg");
			BufferedImage img = ImageIO.read(f);
			byte[] ba = ft.fileTransfer(img.getWidth(), img.getHeight(), img.getRGB(0, 0, img.getWidth(), img.getHeight(), null, 0, img.getWidth()));
			if(ba!= null){
				FileOutputStream fos = new FileOutputStream("D:\\ftpic1.jpg");
				try {
				    fos.write(ba);
				} finally {
				    fos.close();
				}
				System.out.println("Completed");
			}
			else{
				System.out.println("ba is null");
			}
		}catch(Exception e){
			System.out.println("Error: "+e);
		}
	}
}
