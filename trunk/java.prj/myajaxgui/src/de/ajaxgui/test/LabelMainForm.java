package de.ajaxgui.test;

import de.ajaxgui.Label;
import de.ajaxgui.MainForm;

public class LabelMainForm extends MainForm {

	public LabelMainForm() {
		Label label1 = new Label("A label");
		label1.setTop(20);
		label1.setLeft(20);
		this.add(label1);

		Label label2 = new Label("Another label");
		label2.setTop(40);
		label2.setLeft(20);
		this.add(label2);
	}
}
