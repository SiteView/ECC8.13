package ICSharpCode.SharpZipLib.Zip.Compression;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-四月-2010 17:16:49
 */
public class DeflaterHuffman extends Object {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 14-四月-2010 17:16:49
	 */
	public class Tree extends Object {

		private Int32 bl_counts[];
		private Int16 codes[];
		private DeflaterHuffman dh;
		private Int16 freqs[];
		private byte length[];
		private Int32 maxLength;
		private Int32 minNumCodes;
		private Int32 numCodes;

		public Tree(){

		}

		public void finalize() throws Throwable {
			super.finalize();
		}

		/**
		 * 
		 * @param dh
		 * @param elems
		 * @param minCodes
		 * @param maxLength
		 */
		public Tree(DeflaterHuffman dh, Int32 elems, Int32 minCodes, Int32 maxLength){

		}

		public Void BuildCodes(){

		}

		/**
		 * 
		 * @param childs
		 */
		private Void BuildLength(Int32[] childs){

		}

		public Void BuildTree(){

		}

		/**
		 * 
		 * @param blTree
		 */
		public Void CalcBLFreq(Tree blTree){

		}

		public Void CheckEmpty(){

		}

		public Int32 GetEncodedLength(){
			return 0;
		}

		public Int16 getfreqs(){
			return freqs;
		}

		public byte getlength(){
			return length;
		}

		public Int32 getminNumCodes(){
			return minNumCodes;
		}

		public Int32 getnumCodes(){
			return numCodes;
		}

		public Void Reset(){

		}

		/**
		 * 
		 * @param newVal
		 */
		public void setfreqs(Int16 newVal){
			freqs = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setlength(byte newVal){
			length = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setminNumCodes(Int32 newVal){
			minNumCodes = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setnumCodes(Int32 newVal){
			numCodes = newVal;
		}

		/**
		 * 
		 * @param stCodes
		 * @param stLength
		 */
		public Void SetStaticCodes(Int16[] stCodes, Byte[] stLength){

		}

		/**
		 * 
		 * @param code
		 */
		public Void WriteSymbol(Int32 code){

		}

		/**
		 * 
		 * @param blTree
		 */
		public Void WriteTree(Tree blTree){

		}

	}

	private static byte bit4Reverse[];
	private static Int32 BITLEN_NUM;
	private static Int32 BL_ORDER[];
	private Tree blTree;
	private static Int32 BUFSIZE;
	private Int16 d_buf[];
	private static Int32 DIST_NUM;
	private Tree distTree;
	private static Int32 EOF_SYMBOL;
	private Int32 extra_bits;
	private byte l_buf[];
	private Int32 last_lit;
	private static Int32 LITERAL_NUM;
	private Tree literalTree;
	private DeflaterPending pending;
	private static Int32 REP_11_138;
	private static Int32 REP_3_10;
	private static Int32 REP_3_6;
	private static Int16 staticDCodes[];
	private static byte staticDLength[];
	private static Int16 staticLCodes[];
	private static byte staticLLength[];



	public void finalize() throws Throwable {
		super.finalize();
	}

	private DeflaterHuffman(){

	}

	/**
	 * 
	 * @param pending
	 */
	public DeflaterHuffman(DeflaterPending pending){

	}

	/**
	 * 
	 * @param toReverse
	 */
	public static Int16 BitReverse(Int32 toReverse){
		return null;
	}

	public Void CompressBlock(){

	}

	/**
	 * 
	 * @param distance
	 */
	private Int32 Dcode(Int32 distance){
		return 0;
	}

	/**
	 * 
	 * @param stored
	 * @param storedOffset
	 * @param storedLength
	 * @param lastBlock
	 */
	public Void FlushBlock(Byte[] stored, Int32 storedOffset, Int32 storedLength, boolean lastBlock){

	}

	/**
	 * 
	 * @param stored
	 * @param storedOffset
	 * @param storedLength
	 * @param lastBlock
	 */
	public Void FlushStoredBlock(Byte[] stored, Int32 storedOffset, Int32 storedLength, boolean lastBlock){

	}

	public DeflaterPending getpending(){
		return pending;
	}

	public boolean IsFull(){
		return false;
	}

	/**
	 * 
	 * @param len
	 */
	private Int32 Lcode(Int32 len){
		return 0;
	}

	public Void Reset(){

	}

	/**
	 * 
	 * @param blTreeCodes
	 */
	public Void SendAllTrees(Int32 blTreeCodes){

	}

	/**
	 * 
	 * @param newVal
	 */
	public void setpending(DeflaterPending newVal){
		pending = newVal;
	}

	/**
	 * 
	 * @param dist
	 * @param len
	 */
	public boolean TallyDist(Int32 dist, Int32 len){
		return false;
	}

	/**
	 * 
	 * @param lit
	 */
	public boolean TallyLit(Int32 lit){
		return false;
	}

}