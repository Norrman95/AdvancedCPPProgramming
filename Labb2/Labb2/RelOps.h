template <typename Tint, typename R> bool operator!=(const Tint& lhs, const R& rhs) { return !(lhs == rhs); }
template <typename Tint, typename R> bool operator>(const Tint& lhs, const R& rhs) { return (rhs<lhs); }
template <typename Tint, typename R> bool operator>=(const Tint& lhs, const R& rhs) { return !(lhs<rhs); }
template <typename Tint, typename R> bool operator<=(const Tint& lhs, const R& rhs) { return !(rhs<lhs); }