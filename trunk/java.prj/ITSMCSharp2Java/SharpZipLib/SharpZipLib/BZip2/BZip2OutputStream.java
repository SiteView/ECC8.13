package ICSharpCode.SharpZipLib.BZip2;
import ICSharpCode.SharpZipLib.Checksums.IChecksum;

/**
 * @author Administrator
 * @version 1.0
 * @created 14-四月-2010 17:16:45
 */
public class BZip2OutputStream extends Stream {

	/**
	 * @author Administrator
	 * @version 1.0
	 * @created 14-四月-2010 17:16:46
	 */
	private class StackElem extends Object {

		private Int32 dd;
		private Int32 hh;
		private Int32 ll;



		public void finalize() throws Throwable {
			super.finalize();
		}

		public StackElem(){

		}

		public Int32 getdd(){
			return dd;
		}

		public Int32 gethh(){
			return hh;
		}

		public Int32 getll(){
			return ll;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setdd(Int32 newVal){
			dd = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void sethh(Int32 newVal){
			hh = newVal;
		}

		/**
		 * 
		 * @param newVal
		 */
		public void setll(Int32 newVal){
			ll = newVal;
		}

	}

	private Int32 allowableBlockSize;
	private Stream baseStream;
	private byte block[];
	private UInt32 blockCRC;
	private boolean blockRandomised;
	private Int32 blockSize100k;
	private Int32 bsBuff;
	private Int32 bsLive;
	private Int32 bytesOut;
	private static Int32 CLEARMASK;
	private boolean closed;
	private UInt32 combinedCRC;
	private Int32 currentChar;
	private static Int32 DEPTH_THRESH;
	private boolean firstAttempt;
	private Int32 ftab[];
	private static Int32 GREATER_ICOST;
	private Int32 incs[];
	private boolean inUse[];
	private Int32 last;
	private static Int32 LESSER_ICOST;
	private IChecksum mCrc;
	private Int32 mtfFreq[];
	private Int32 nBlocksRandomised;
	private Int32 nInUse;
	private Int32 nMTF;
	private Int32 origPtr;
	private static Int32 QSORT_STACK_SIZE;
	private Int32 quadrant[];
	private Int32 runLength;
	private char selector[];
	private char selectorMtf[];
	private char seqToUnseq[];
	private static Int32 SETMASK;
	private static Int32 SMALL_THRESH;
	private Int16 szptr[];
	private char unseqToSeq[];
	private Int32 workDone;
	private Int32 workFactor;
	private Int32 workLimit;
	private Int32 zptr[];



	public void finalize() throws Throwable {
		super.finalize();
	}

	/**
	 * 
	 * @param inStream
	 */
	public BZip2OutputStream(Stream inStream){

	}

	/**
	 * 
	 * @param inStream
	 * @param inBlockSize
	 */
	public BZip2OutputStream(Stream inStream, Int32 inBlockSize){

	}

	private BZip2OutputStream(){

	}

	private Void AllocateCompressStructures(){

	}

	private Void BsFinishedWithStream(){

	}

	/**
	 * 
	 * @param u
	 */
	private Void BsPutint(Int32 u){

	}

	/**
	 * 
	 * @param numBits
	 * @param c
	 */
	private Void BsPutIntVS(Int32 numBits, Int32 c){

	}

	/**
	 * 
	 * @param c
	 */
	private Void BsPutUChar(Int32 c){

	}

	/**
	 * 
	 * @param f
	 */
	private Void BsSetStream(Stream f){

	}

	/**
	 * 
	 * @param n
	 * @param v
	 */
	private Void BsW(Int32 n, Int32 v){

	}

	public boolean CanRead(){
		return false;
	}

	public boolean CanSeek(){
		return false;
	}

	public boolean CanWrite(){
		return false;
	}

	public Void Close(){

	}

	private Void DoReversibleTransformation(){

	}

	private Void EndBlock(){

	}

	private Void EndCompression(){

	}

	public Void Finalize(){

	}

	public Void Flush(){

	}

	/**
	 * 
	 * @param i1
	 * @param i2
	 */
	private boolean FullGtU(Int32 i1, Int32 i2){
		return false;
	}

	private Void GenerateMTFValues(){

	}

	/**
	 * 
	 * @param code
	 * @param length
	 * @param minLen
	 * @param maxLen
	 * @param alphaSize
	 */
	private Void HbAssignCodes(Int32[] code, Char[] length, Int32 minLen, Int32 maxLen, Int32 alphaSize){

	}

	/**
	 * 
	 * @param len
	 * @param freq
	 * @param alphaSize
	 * @param maxLen
	 */
	private static Void HbMakeCodeLengths(Char[] len, Int32[] freq, Int32 alphaSize, Int32 maxLen){

	}

	private Void InitBlock(){

	}

	private Void Initialize(){

	}

	public Int64 Length(){
		return null;
	}

	private Void MainSort(){

	}

	private Void MakeMaps(){

	}

	/**
	 * 
	 * @param a
	 * @param b
	 * @param c
	 */
	private byte Med3(byte a, byte b, byte c){
		return 0;
	}

	private Void MoveToFrontCodeAndSend(){

	}

	private static Void Panic(){

	}

	public Int64 Position(){
		return null;
	}

	/**
	 * 
	 * @param loSt
	 * @param hiSt
	 * @param dSt
	 */
	private Void QSort3(Int32 loSt, Int32 hiSt, Int32 dSt){

	}

	private Void RandomiseBlock(){

	}

	/**
	 * 
	 * @param b
	 * @param off
	 * @param len
	 */
	public Int32 Read(Byte[] b, Int32 off, Int32 len){
		return 0;
	}

	public Int32 ReadByte(){
		return 0;
	}

	/**
	 * 
	 * @param offset
	 * @param origin
	 */
	public Int64 Seek(Int64 offset, SeekOrigin origin){
		return null;
	}

	private Void SendMTFValues(){

	}

	/**
	 * 
	 * @param val
	 */
	public Void SetLength(Int64 val){

	}

	/**
	 * 
	 * @param lo
	 * @param hi
	 * @param d
	 */
	private Void SimpleSort(Int32 lo, Int32 hi, Int32 d){

	}

	/**
	 * 
	 * @param p1
	 * @param p2
	 * @param n
	 */
	private Void Vswap(Int32 p1, Int32 p2, Int32 n){

	}

	/**
	 * 
	 * @param buf
	 * @param off
	 * @param len
	 */
	public Void Write(Byte[] buf, Int32 off, Int32 len){

	}

	/**
	 * 
	 * @param bv
	 */
	public Void WriteByte(byte bv){

	}

	private Void WriteRun(){

	}

}