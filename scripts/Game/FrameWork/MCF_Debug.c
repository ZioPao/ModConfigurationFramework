class MCF_Debug 
{
	ref static array<ref Shape> dbgShapes;

	
	// Debug stuff
	static void DrawSphereAtPos(vector pos, int color)
	{
		vector matx[4];
		Math3D.MatrixIdentity4(matx);
		matx[3] = pos;
		int shapeFlags = ShapeFlags.DEFAULT;
		Shape s = Shape.CreateSphere(color, shapeFlags, pos, 0.05);
		s.SetMatrix(matx);
		dbgShapes.Insert(s);
	}
	
	

}