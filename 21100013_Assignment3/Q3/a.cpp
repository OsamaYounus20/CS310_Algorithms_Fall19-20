solve(indexr, (indexr+midr)/2, startc, (startc+ midc)/2, row, col);
			solve(indexr, (indexr+midr)/2, midc, (midc-startc)/2+midc, midr-1, midc);
			solve(midr, (midr-indexr)/2+midr, startc, (startc+ midc)/2, midr, midc-1);
			solve(midr, (midr-indexr)/2+midr, midc, (midc-startc)/2+midc, midr, midc);