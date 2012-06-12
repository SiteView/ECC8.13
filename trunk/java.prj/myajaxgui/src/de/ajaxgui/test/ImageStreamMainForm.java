package de.ajaxgui.test;

import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;

import javax.imageio.ImageIO;

import de.ajaxgui.ImageStream;
import de.ajaxgui.MainForm;

public class ImageStreamMainForm extends MainForm {

	public ImageStreamMainForm() {
		ImageStream is = new ImageStream();
		is.setLocation(60, 60);
		this.add(is);

		BufferedImage bi = null;
		try {
			bi = ImageIO
					.read(new URL(
							"http://www.google.cn/images/nav_logo7.png"));
		} catch (MalformedURLException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

		is.createImage(bi, ImageStream.Format.PNG);
		is.send();
	}
}
