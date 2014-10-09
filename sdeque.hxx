#include <deque>
#include <initializer_list>
#include <iterator>
#include <list>
#include <memory>


// Based off std::deque. However, this allows for iterators that remain valid unless their value is removed from the deque.

template <class T, class Allocator = std::allocator<T> >
class sdeque
{
  private:

    struct node;
    class const_node_iterator;
    class node_iterator;

  public:

    typedef T value_type;
    typedef Allocator allocator_type;

    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef node_iterator                            iterator;
    typedef const_node_iterator                      const_iterator;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

  private:

    struct node
    {
        node* prev;
        T value;
        node* next;

        node(const T& new_value) : prev(nullptr), value(new_value), next(nullptr) {}
        node(T&& new_value) : prev(nullptr), value(std::move(new_value)), next(nullptr) {}

        node(const T& new_value, node* new_next) : prev(nullptr), value(new_value), next(new_next) {}
        node(T&& new_value, node* new_next) : prev(nullptr), value(std::move(new_value)), next(new_next) {}

        node(node* new_prev, const T& new_value) : prev(new_prev), value(new_value), next(nullptr) {}
        node(node* new_prev, T&& new_value) : prev(new_prev), value(std::move(new_value)), next(nullptr) {}

        node(node* new_prev, const T& new_value, node* new_next) : prev(new_prev), value(new_value), next(new_next) {}
        node(node* new_prev, T&& new_value, node* new_next) : prev(new_prev), value(std::move(new_value)), next(new_next) {}
    };

    class const_node_iterator
    {
      public:

        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::bidirectional_iterator_tag iterator_category;

      public:

        const_node_iterator()  = default;
        const_node_iterator(const const_node_iterator&) = default;
        const_node_iterator(const_node_iterator&&) = default;

        const_node_iterator(std::nullptr_t nulp) : pos(nullptr) {}

        ~const_node_iterator() = default;

        const_node_iterator& operator=(const const_node_iterator&) = default;
        const_node_iterator& operator=(const_node_iterator&&) = default;

        const reference operator*() const
        {
            return(this->node->value);
        }

        const pointer operator->() const
        {
            return(&(this->node->value));
        }

        const_node_iterator& operator++()
        {
            if (this->pos != nullptr)
            {
                this->pos = this->pos->next;
            }

            return(*this);
        }

        const_node_iterator operator++(int)
        {
            const_node_iterator that(*this);

            ++(*this);

            return(that);
        }

        const_node_iterator& operator--()
        {
            if (this->pos != nullptr)
            {
                this->pos = this->pos->prev;
            }

            return(*this);
        }

        const_node_iterator operator--(int)
        {
            const_node_iterator that(*this);

            --(*this);

            return(that);
        }

        inline bool operator==(const const_node_iterator& that) const
        {
            return(this->pos == that.pos);
        }

        inline bool operator!=(const const_node_iterator& that) const
        {
            return(this->pos != that.pos);
        }

      protected:

        const_node_iterator(const node*& new_pos) : pos(new_pos) {}
        const_node_iterator(node*&& new_pos) : pos(std::move(new_pos)) {}

      protected:

        node* pos;
    };

    class node_iterator : public const_node_iterator
    {
      public:

        node_iterator()  = default;
        node_iterator(const const_node_iterator&) = default;
        node_iterator(const_node_iterator&&) = default;
        node_iterator(const node_iterator&) = default;
        node_iterator(node_iterator&&) = default;

        node_iterator(std::nullptr_t nulp) : const_node_iterator(nullptr) {}

        ~node_iterator() = default;

        node_iterator& operator=(const node_iterator&) = default;
        node_iterator& operator=(node_iterator&&) = default;
        node_iterator& operator=(const node_iterator&&) = default;

        inline bool operator==(const node_iterator& that) const
        {
            return(this->pos == that.pos);
        }

        inline bool operator!=(const node_iterator& that) const
        {
            return(this->pos != that.pos);
        }

        reference operator*()
        {
            return(this->node->value);
        }

        pointer operator->()
        {
            return(&(this->node->value));
        }

        node_iterator& operator++()
        {
            if (this->pos != nullptr)
            {
                this->pos = this->pos->next;
            }

            return(*this);
        }

        node_iterator operator++(int)
        {
            node_iterator that(*this);

            ++(*this);

            return(that);
        }

        node_iterator& operator--()
        {
            if (this->pos != nullptr)
            {
                this->pos = this->pos->prev;
            }

            return(*this);
        }

        node_iterator operator--(int)
        {
            node_iterator that(*this);

            --(*this);

            return(that);
        }

      protected:

        node_iterator(const node*& new_pos) : const_node_iterator(new_pos) {}
        node_iterator(node*&& new_pos) : const_node_iterator(std::move(new_pos)) {}
    };

    typedef std::deque< node, typename std::allocator_traits<Allocator>::template rebind_alloc<node> > deque;

  private:

    deque internal_deque;

  public:

    explicit sdeque(const allocator_type& alloc = allocator_type()) : internal_deque(alloc) {}

    explicit sdeque(size_type n,
                    const value_type& val = value_type(),
                    const allocator_type& alloc = allocator_type()) : internal_deque(alloc)
    {
        node* prev = nullptr;

        if (n > 0)
        {
            this->internal_deque.emplace_back(val);
            prev = &(this->internal_deque.back());
        }
        for (size_type i = 1; i < n; i++)
        {
            this->internal_deque.emplace_back(prev, val);
            prev->next = &(this->internal_deque.back());
            prev = prev->next;
        }
    }

    template <class InputIterator>
    sdeque(InputIterator first, InputIterator last,
            const allocator_type& alloc = allocator_type()) : internal_deque(alloc)
    {
        InputIterator i = first;
        node* prev = nullptr;

        if (i != last)
        {
            this->internal_deque.emplace_back(*i);
            prev = &(this->internal_deque.back());
            i++;
        }
        for (; i != last; i++)
        {
            this->internal_deque.emplace_back(prev, i->value);
            prev->next = &(this->internal_deque.back());
            prev = prev->next;
        }
    }

    sdeque(const sdeque& that,
            const allocator_type& alloc = allocator_type()) : internal_deque(that.begin(), that.end(), alloc) {}

    sdeque(sdeque&& ) = default;

    sdeque(sdeque&& that, const allocator_type& alloc) : internal_deque(std::move(that.internal_deque), alloc) {}

    sdeque(std::initializer_list<value_type> il,
            const allocator_type& alloc = allocator_type()) : internal_deque(il.begin(), il.end(), alloc) {}

    ~sdeque() = default;

    sdeque& operator=(const sdeque& that)
    {
        if (this != &that)
        {
            this->clear();

            sdeque::const_iterator i = that.begin();
            node* prev = nullptr;

            if (i != that.end())
            {
                this->internal_deque.emplace_back(*i);
                prev = &(this->internal_deque.back());
                i++;
            }
            for (; i != that.end(); i++)
            {
                this->internal_deque.emplace_back(prev, i->value);
                prev->next = &(this->internal_deque.back());
                prev = prev->next;
            }
        }

        return(*this);
    }

    sdeque& operator=(sdeque&& ) = default;


    reference operator[] (size_type n)
    {
        return(this->internal_deque[n].value);
    }

    const_reference operator[] (size_type n) const
    {
        return(this->internal_deque[n].value);
    }

    reference at (size_type n)
    {
        return(this->internal_deque.at(n).value);
    }

    const_reference at (size_type n) const
    {
        return(this->internal_deque.at(n).value);
    }

    inline reference back()
    {
        return(this->internal_deque.back().value);
    }

    inline const_reference back() const
    {
        return(this->internal_deque.back().value);
    }

    inline iterator begin() noexcept
    {
        return(iterator(&(this->internal_deque.front())));
    }

    inline const_iterator begin() const noexcept
    {
        return(const_iterator(&(this->internal_deque.front())));
    }

    inline const_iterator cbegin() const noexcept
    {
        return(const_iterator(&(this->internal_deque.front())));
    }

    inline const_iterator cend() const noexcept
    {
        return(const_iterator());
    }

    inline void clear() noexcept
    {
        this->internal_deque.clear();
    }

    inline const_iterator crbegin() const noexcept
    {
        return(const_iterator(&(this->internal_deque.back())));
    }

    inline const_iterator crend() const noexcept
    {
        return(const_iterator());
    }

    inline bool empty() const noexcept
    {
        return(this->internal_deque.empty());
    }

    inline iterator end() noexcept
    {
        return(iterator());
    }

    inline const_iterator end() const noexcept
    {
        return(const_iterator());
    }

    inline reference front()
    {
        return(this->internal_deque.front().value);
    }

    inline const_reference front() const
    {
        return(this->internal_deque.front().value);
    }

    inline size_type max_size() const noexcept
    {
        return(this->internal_deque.max_size());
    }

    void pop_back()
    {
        this->internal_deque.pop_back();
        if (this->size() > 0)
        {
            this->internal_deque.back().next = nullptr;
        }
    }

    void pop_front()
    {
        this->internal_deque.pop_front();
        if (this->size() > 0)
        {
            this->internal_deque.front().prev = nullptr;
        }
    }

    template <class... Args>
    void emplace_back(Args&&... args)
    {
        if (this->size() > 0)
        {
            node *prev = &(this->internal_deque.back());
            this->internal_deque.emplace_back(prev, std::move(value_type(std::forward< Args >(args)...)));
            prev->next = &(this->internal_deque.back());
        }
        else
        {
            this->internal_deque.emplace_back(std::move(value_type(std::forward< Args >(args)...)));
        }
    }

    template <class... Args>
    void emplace_front(Args&&... args)
    {
        if (this->size() > 0)
        {
            node *next = &(this->internal_deque.front());
            this->internal_deque.emplace_front(std::move(value_type(std::forward< Args >(args)...)), next);
            next->prev = &(this->internal_deque.front());
        }
        else
        {
            this->internal_deque.emplace_front(std::move(value_type(std::forward< Args >(args)...)));
        }
    }

    void push_back(const value_type& val)
    {
        if (this->size() > 0)
        {
            node *prev = &(this->internal_deque.back());
            this->internal_deque.emplace_back(prev, val);
            prev->next = &(this->internal_deque.back());
        }
        else
        {
            this->internal_deque.emplace_back(val);
        }
    }

    void push_back(value_type&& val)
    {
        if (this->size() > 0)
        {
            node *prev = &(this->internal_deque.back());
            this->internal_deque.emplace_back(prev, std::move(val));
            prev->next = &(this->internal_deque.back());
        }
        else
        {
            this->internal_deque.emplace_back(std::move(val));
        }
    }

    void push_front(const value_type& val)
    {
        if (this->size() > 0)
        {
            node *next = &(this->internal_deque.front());
            this->internal_deque.emplace_front(val, next);
            next->prev = &(this->internal_deque.front());
        }
        else
        {
            this->internal_deque.emplace_front(val);
        }
    }

    void push_front(value_type&& val)
    {
        if (this->size() > 0)
        {
            node *next = &(this->internal_deque.front());
            this->internal_deque.emplace_front(std::move(val), next);
            next->prev = &(this->internal_deque.front());
        }
        else
        {
            this->internal_deque.emplace_front(std::move(val));
        }
    }

    inline iterator rbegin() noexcept
    {
        return(iterator(&(this->internal_deque.back())));
    }

    inline const_iterator rbegin() const noexcept
    {
        return(const_iterator(&(this->internal_deque.back())));
    }

    inline iterator rend() noexcept
    {
        return(iterator());
    }

    inline const_iterator rend() const noexcept
    {
        return(const_iterator());
    }

    void resize(size_type n, const value_type& val = value_type())
    {
        if (n < this->size())
        {
            if (n > 0)
            {
                this->internal_deque[n-1].next = nullptr;
            }

            this->internal_deque.resize(n);
        }
        else
        {
            for (size_type i = this->size(); i < n; i++)
            {
                this->push_back(val);
            }
        }
    }

    inline void shrink_to_fit()
    {
        this->internal_deque.shrink_to_fit();
    }

    inline size_type size() const noexcept
    {
        return(this->internal_deque.size());
    }

    inline void swap(sdeque& that)
    {
        this->internal_deque.swap(that.internal_deque);
    }

};
