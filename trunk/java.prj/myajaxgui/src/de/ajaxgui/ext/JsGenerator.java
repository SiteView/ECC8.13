package de.ajaxgui.ext;

public class JsGenerator {
	private static final ThreadLocal<JsGenerator> jsGenerator = new ThreadLocal<JsGenerator>();

	public static JsGenerator get() {
		return jsGenerator.get();
	}

	public static void set(JsGenerator jg) {
		jsGenerator.set(jg);
	}

	private String code = "";

	public void add(String code) {
		// System.out.println("JsG: add(" + code + ")");
		this.code += code;
	}

	public void addLine(String code) {
		// System.out.println("JsG: addLine(" + code + ")");
		this.code += code + "\n";
	}

	public String getCode() {
		// System.out.println("JsG: getCode()");
		String code = this.code;
		clear();
		// System.out.println(code);
		return code;
	}

	public void clear() {
		code = "";
	}
}
