package de.ajaxgui.test;

import de.ajaxgui.Button;
import de.ajaxgui.MainForm;
import de.ajaxgui.layout.FlowLayout;

public class FlowLayoutMainForm extends MainForm {

	public FlowLayoutMainForm() {
		FlowLayout fl = new FlowLayout();
		fl.setLocation(20, 20);
		fl.setDimension(320, 240);
		fl.setHorizontalSpacing(2);
		this.add(fl);

		Button btn1 = new Button("Button 1");
		fl.add(btn1);

		Button btn2 = new Button("Button 2", "themes/icons/kids/16/apply.png");
		fl.add(btn2);

		Button btn3 = new Button("This is another Button");
		fl.add(btn3);
	}
}
