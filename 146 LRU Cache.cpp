class LRUCache
{
public:
    LRUCache(int capacity) : cap(capacity)
    {

    }
    
    int get(int key)
    {
        auto it = map.find(key);
        
        if (it == map.end()) return -1;
    
        Slot slot = it->second;
        hit(slot);
        return slot->second;
    }
    
    void put(int key, int value)
    {
        if (cap <= 0) return;
        
        auto it = map.find(key);
        if (it != map.end())
        {
            Slot slot = it->second;
            slot->second = value;
            hit(slot);
            return;
        }
        
        if (linkl.size() < cap)
        {
            /* insert into list directly */
            linkl.emplace_front(key, value);
        }
        else
        {
            /* find victim slot */
            auto slot = std::prev(linkl.end());
            /* remove from map */
            map.erase(slot->first);
            /* set slot */
            slot->first = key;
            slot->second = value;
            hit(slot);
        }
        /* put into map */
        map.insert(std::pair<int, Slot>(key, linkl.begin()));
    }
    
private:
    typedef std::list<std::pair<int, int>>::iterator Slot;
    int cap;
    std::unordered_map<int, Slot> map;
    std::list<std::pair<int, int>> linkl; // 这里其实没必要存pair，存个key再通过map取value就行了

    void hit(Slot slot)
    {
        if (slot == linkl.begin()) return;
        /* move to head */
        linkl.splice(linkl.begin(), linkl, slot, std::next(slot));
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
