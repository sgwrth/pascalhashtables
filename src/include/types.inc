type
  BucketsLenSpan = 1..BucketInitialCapacity;

  Key = packed array [1..KeyMaxLen] of char;

  Node = record
    NextNode: ^Node;
    Key: Key;
    HashedKey: integer;
    Value: integer;
  end;

  NodePtr = ^Node;

  HashTableBuckets = array [BucketsLenSpan] of NodePtr;

  HashTable = record
    Buckets: HashTableBuckets;
    Length: integer;
    Capacity: integer;
  end;

  HashTablePtr = ^HashTable;

