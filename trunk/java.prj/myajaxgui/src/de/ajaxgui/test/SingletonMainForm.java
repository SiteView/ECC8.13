package de.ajaxgui.test;

import de.ajaxgui.Label;
import de.ajaxgui.MainForm;

public class SingletonMainForm extends MainForm {

	private Label label = null;

	public SingletonMainForm() {
		MySingleton ms = MySingleton.getMySingleton();
		label = new Label(ms.getText());
		label.setTop(80);
		label.setLeft(50);
		this.add(label);
	}
}
