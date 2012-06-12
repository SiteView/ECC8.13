package de.ajaxgui.test;

import de.ajaxgui.Button;
import de.ajaxgui.MainForm;
import de.ajaxgui.layout.HorizontalBoxLayout;

public class HorizontalBoxLayoutMainForm extends MainForm {

	public HorizontalBoxLayoutMainForm() {
		HorizontalBoxLayout hbl1 = new HorizontalBoxLayout();
		hbl1.setLocation(20, 20);
		this.add(hbl1);
		hbl1.add(new Button("Button 1"));
		hbl1.add(new Button("Button 2", "themes/icons/kids/16/apply.png"));
		hbl1.add(new Button("This is another Button"));

		HorizontalBoxLayout hbl2 = new HorizontalBoxLayout();
		hbl2.setLocation(20, 60);
		hbl2.setWidth(400);
		hbl2.setSpacing(4);
		this.add(hbl2);
		hbl2.add(new Button("Button 1"), 1);
		hbl2.add(new Button("Button 2", "themes/icons/kids/16/apply.png"), 1);
		hbl2.add(new Button("This is another Button"), 1);

		HorizontalBoxLayout hbl3 = new HorizontalBoxLayout();
		hbl3.setLocation(20, 100);
		hbl3.setWidth(400);
		hbl3.setAlignment(HorizontalBoxLayout.Alignment.RIGHT);
		this.add(hbl3);
		hbl3.add(new Button("Button 1"));
		hbl3.add(new Button("Button 2", "themes/icons/kids/16/apply.png"));
		hbl3.add(new Button("This is another Button"));
	}
}
