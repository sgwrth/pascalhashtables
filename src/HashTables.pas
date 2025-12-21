program HashTables;

{$I include/constants.inc}

{$I include/types.inc}

var
  Table: HashTable;

{$I include/proceduresandfunctions.inc}

begin
  InitTable(Table);
  Table.Buckets[1] := NewNode('foo', 42);
  writeln(Table.Buckets[1]^.Key);
  writeln(Table.Buckets[1]^.Value:0);
  writeln(Table.Buckets[1]^.HashedKey:0);
end.
