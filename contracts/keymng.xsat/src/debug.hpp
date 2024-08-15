template <typename T>
void keymng::clear_table(T& table, uint64_t rows_to_clear) {
    auto itr = table.begin();
    while (itr != table.end() && rows_to_clear--) {
        itr = table.erase(itr);
    }
}

[[eosio::action]]
void keymng::cleartable(const name table_name, const optional<name> scope, const optional<uint64_t> max_rows) {
    require_auth(get_self());
    const uint64_t rows_to_clear = (!max_rows || *max_rows == 0) ? -1 : *max_rows;
    const uint64_t value = scope ? scope->value : get_self().value;

    if (table_name == "globalid"_n) {
        _global_id.remove();
    } else if (table_name == "nodes"_n) {
        keymng_index _keymng(get_self(), get_self().value);
        clear_table(_keymng, rows_to_clear);
    } else {
        check(false, "keymng::cleartable: [table_name] unknown table to clear");
    }
}


