package de.ajaxgui.test;

import de.ajaxgui.Button;
import de.ajaxgui.ComboBox;
import de.ajaxgui.Image;
import de.ajaxgui.Label;
import de.ajaxgui.MainForm;
import de.ajaxgui.layout.GridLayout;

public class GridLayoutMainForm extends MainForm {

	public GridLayoutMainForm() {
		Image img = new Image("test/grid_dialog_box.png");
		img.setLocation(20, 48);
		this.add(img);

		GridLayout gl = new GridLayout(4, 5);
		gl.setLocation(46, 300);
		this.add(gl);

		gl.setDrawBorder(true);
		gl.setPadding(4);
		gl.setRowVerticalAlignment(1, GridLayout.VerticalAlignment.MIDDLE);

		gl.setHorizontalSpacing(4);
		gl.setVerticalSpacing(4);

		gl.setColumnWidth(0, 40);
		gl.setColumnWidth(1, 35);
		gl.setColumnWidth(2, 75);
		gl.setColumnWidth(3, 75);
		gl.setColumnWidth(4, 75);

		gl.setRowHeight(0, 30);
		gl.setRowHeight(1, 30);
		gl.setRowHeight(2, 15);
		gl.setRowHeight(3, 25);

		gl.mergeCells(1, 0, 4, 1);
		gl.mergeCells(1, 1, 4, 1);

		gl.add(new Image("themes/icons/kids/32/appearance.png"), 0, 0);
		gl.add(new Label("Open:"), 0, 1);
		Button b1 = new Button("Ok");
		b1.setAllowStretchX(true);
		gl.add(b1, 2, 3);
		Button b2 = new Button("Cancel");
		b2.setAllowStretchX(true);
		gl.add(b2, 3, 3);
		Button b3 = new Button("Browse...");
		b3.setAllowStretchX(true);
		gl.add(b3, 4, 3);
		gl
				.add(
						new Label(
								"Type in the name of a program, folder, document or<br/> Internet Resource and Windows will open it for you."),
						1, 0);
		gl.add(new ComboBox(), 1, 1);
	}
}
