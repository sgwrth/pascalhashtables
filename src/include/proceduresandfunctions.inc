(* Forward declarations. *)
procedure InitTable(Table: HashTablePtr); forward;
procedure InitBucket(var Bucket: NodePtr); forward;
function NewNode(Key: Key; Value: integer) : NodePtr; forward;
procedure InitNode(var Node: NodePtr; Key: Key; Value: integer); forward;
function GetHashedKey(Key: Key) : integer; forward;
function TargetBucket(HashedKey: integer; Capacity: integer) : integer; forward;
function IsFinalNode(Node: NodePtr) : boolean; forward;
procedure AppendNode(Table: HashTablePtr; Key: Key; Value: integer); forward;

procedure InitTable(Table: HashTablePtr);
var
  I: integer;
  Buckets: HashTableBuckets;
begin
  for I := 1 to BucketInitialCapacity do
    InitBucket(Buckets[I]);
  Table^.Buckets := Buckets;
  Table^.Length := 0;
  Table^.Capacity := BucketInitialCapacity;
end;

procedure InitBucket(var Bucket: NodePtr);
begin
  Bucket := nil;
end;

function NewNode(Key: Key; Value: integer) : NodePtr;
var
  Node: NodePtr;
begin
  new(Node);
  InitNode(Node, Key, Value);
  NewNode := Node;
end;

procedure InitNode(var Node: NodePtr; Key: Key; Value: integer);
begin
  Node^.NextNode := nil;
  Node^.Key := Key;
  Node^.HashedKey := GetHashedKey(Key);
  Node^.Value := Value;
end;

function GetHashedKey(Key: Key) : integer;
var
  HashedKey: integer;
  OrdinalValue: integer;
  Pos: integer;
begin
  HashedKey := 0;
  Pos := 1;
  while (Pos <= KeyMaxLen) and (ord(Key[Pos]) <> 0) do
  begin
    OrdinalValue := ord(Key[Pos]);
    HashedKey := HashedKey * 31 + OrdinalValue;
    Pos := Pos + 1;
  end;
  GetHashedKey := HashedKey; 
end;

function TargetBucket(HashedKey: integer; Capacity: integer) : integer;
begin
  TargetBucket := abs(HashedKey) mod Capacity + 1;
end;

function IsFinalNode(Node: NodePtr) : boolean;
begin
  IsFinalNode := Node^.NextNode = nil;
end;

procedure AppendNode(Table: HashTablePtr; Key: Key; Value: integer);
var
  Node: NodePtr;
  BucketNumber: integer;
  CurrentNode: NodePtr;
begin
  Node := NewNode(Key, Value);
  BucketNumber := TargetBucket(Node^.HashedKey, Table^.Capacity);
  if Table^.Buckets[BucketNumber] = nil then
    Table^.Buckets[BucketNumber] = Node
  else
  begin
    CurrentNode := Table^.Buckets[BucketNumber];
    while IsFinalNode(CurrentNode) = false do
      CurrentNode := CurrentNode^.NextNode;
    CurrentNode^.NextNode := Node;
  end;
end;
