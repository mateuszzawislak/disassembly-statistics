#ifndef ROW_H
#define ROW_H

class Row
{
public:
	enum RowType
	{
		FIRST_ROW = 0,
		NEXT_ROW = 1
	};

	Row(void);
	~Row(void);
	
	virtual Row::RowType getType() = 0 ;
};

#endif
