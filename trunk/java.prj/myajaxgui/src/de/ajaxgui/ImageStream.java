package de.ajaxgui;

import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.IOException;

import javax.imageio.ImageIO;

import de.ajaxgui.ext.ComponentManager;

public class ImageStream extends Image {
	public static enum Format {
		JPEG, PNG
	}

	private ImageStream.Format format = null;

	private byte[] image = null;

	private int dummy = 0;

	public ImageStream() {
		super("");
	}

	public void createImage(BufferedImage bufferedImage,
			ImageStream.Format format) {
		this.format = format;
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		try {
			switch (format) {
			case JPEG:
				ImageIO.write(bufferedImage, "jpeg", baos);
				break;
			case PNG:
				ImageIO.write(bufferedImage, "png", baos);
				break;
			}
			baos.flush();
			image = baos.toByteArray();
			baos.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public ImageStream.Format getFormat() {
		return format;
	}

	public byte[] getImage() {
		return image;
	}

	public void send() {
		this.setUri(ComponentManager.get().getServletURI() + "/imageStream?id="
				+ this.getId() + "&dummy=" + dummy);
		dummy++;
	}
}
