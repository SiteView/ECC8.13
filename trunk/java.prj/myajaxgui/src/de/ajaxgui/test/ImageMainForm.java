package de.ajaxgui.test;

import de.ajaxgui.Button;
import de.ajaxgui.Image;
import de.ajaxgui.MainForm;

public class ImageMainForm extends MainForm {

	private Image img = null;

	public ImageMainForm() {
		img = new Image("themes/icons/kids/32/sound.png");
		img.setLocation(60, 60);
		this.add(img);

		Button btn1 = new Button("Set image 1");
		btn1.setTop(100);
		btn1.setLeft(10);
		btn1.addClick(this, "btn1Clicked");
		this.add(btn1);

		Button btn2 = new Button("Set image 2");
		btn2.setTop(100);
		btn2.setLeft(90);
		btn2.addClick(this, "btn2Clicked");
		this.add(btn2);

	}

	public void btn1Clicked() {
		img.setUri("themes/icons/kids/32/outbox.png");
	}

	public void btn2Clicked() {
		img.setUri("themes/icons/kids/32/accessibility.png");
	}

}
